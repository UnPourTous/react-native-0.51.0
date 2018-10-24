// Copyright 2004-present Facebook. All Rights Reserved.

#include "JSUnBundleSdCardBundle.h"

#include <cstdint>
#include <fb/assert.h>
#include <libgen.h>
#include <memory>
#include <sstream>
#include <sys/endian.h>
#include <utility>
#include <fb/log.h>

#include <folly/Memory.h>
#include <sys/stat.h>

#include <android/log.h>
#define APPNAME "eric-rn jni"
#define LOGD(TAG) __android_log_print(ANDROID_LOG_DEBUG, APPNAME, TAG);

const std::string MAGIC_FILE_NAME = "UNBUNDLE";

namespace facebook {
namespace react {

static std::string jsModulesDir(const std::string& entryFile) {
  std::string dir = dirname(entryFile.c_str());

  // android's asset manager does not work with paths that start with a dot
  return dir == "." ? "js-modules/" : dir + "/js-modules/";
}

std::unique_ptr<JSUnBundleSdCardBundle> JSUnBundleSdCardBundle::fromEntryFile(const std::string& entryFile) {
  return folly::make_unique<JSUnBundleSdCardBundle>(jsModulesDir(entryFile));
}

JSUnBundleSdCardBundle::JSUnBundleSdCardBundle(const std::string& moduleDirectory) :
  m_moduleDirectory(moduleDirectory) {}

bool JSUnBundleSdCardBundle::isUnbundle(const std::string& sourceURL) {
  LOGD("JSUnBundleSdCardBundle::isUnbundle");
  auto magicFileName = jsModulesDir(sourceURL) + MAGIC_FILE_NAME;
  __android_log_print(ANDROID_LOG_DEBUG, "eric-rn jni", "%s", magicFileName.c_str());

  struct stat buffer;
  // 有MAGIC_FILE_NAME就表示是unbundle包
  return (stat (magicFileName.c_str(), &buffer) == 0);
}

JSUnBundleSdCardBundle::Module JSUnBundleSdCardBundle::getModule(uint32_t moduleId) const {
  // can be nullptr for default constructor.
  // FBASSERTMSGF(m_assetManager != nullptr, "Unbundle has not been initialized with an asset manager");
  LOGD("JniJSModulesUnbundle::isUnbundle hahahhahahahahhahahh ");

  std::ostringstream sourceUrlBuilder;
  sourceUrlBuilder << moduleId << ".js";
  auto sourceUrl = sourceUrlBuilder.str();

  auto fileName = m_moduleDirectory + sourceUrl;

  std::ifstream ifs (fileName);
  if (ifs.good()) {
    LOGD("JniJSModulesUnbundle::isUnbundle hahahhahah 1");
    std::filebuf* pbuf = ifs.rdbuf();
    std::size_t size = pbuf->pubseekoff(0, ifs.end, ifs.in);
    pbuf->pubseekpos (0, ifs.in);
    char* buffer = new char[size];
    pbuf->sgetn (buffer, size);
    ifs.close();
    std::string code(buffer, size);
    delete[] buffer;
    LOGD("JniJSModulesUnbundle::isUnbundle hahahhahah 2");
    return {sourceUrl, code};
  } else {
    throw ModuleNotFound("Module not found: " + sourceUrl);
  }
}

// fixme 虚析构函数应该如何实现
JSUnBundleSdCardBundle::~JSUnBundleSdCardBundle() {}

}  // namespace react
}  // namespace facebook
