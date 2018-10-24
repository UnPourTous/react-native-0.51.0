// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include <fstream>
#include <memory>

#include <cxxreact/JSBigString.h>
#include <cxxreact/JSModulesUnbundle.h>

namespace facebook {
namespace react {

class JSUnBundleSdCardBundle : public JSModulesUnbundle {
public:
  JSUnBundleSdCardBundle() = default;
  JSUnBundleSdCardBundle(const std::string& moduleDirectory);
  ~JSUnBundleSdCardBundle();

  // Throws std::runtime_error on failure.
  Module getModule(uint32_t moduleId) const override;

  static std::unique_ptr<JSUnBundleSdCardBundle> fromEntryFile(const std::string& entryFile);

  static bool isUnbundle(const std::string& sourceURL);
private:
  std::string m_moduleDirectory;
};
}  // namespace react
}  // namespace facebook
