// Copyright 2004-present Facebook. All Rights Reserved.

#include "JSUnBundleSdCardRegistry.h"

#include "JSUnBundleSdCardBundle.h"
#include <folly/Memory.h>

namespace facebook {
namespace react {

JSUnBundleSdCardRegistry::JSUnBundleSdCardRegistry(std::unique_ptr<JSModulesUnbundle> mainBundle, const std::string& baseDirectoryPath):
RAMBundleRegistry(std::move(mainBundle)), m_baseDirectoryPath(baseDirectoryPath) {}

std::unique_ptr<JSModulesUnbundle> JSUnBundleSdCardRegistry::bundleById(uint32_t index) const {
  std::string bundlePathById = m_baseDirectoryPath + folly::to<std::string>(index) + "/js-modules/";
  return folly::make_unique<JSUnBundleSdCardBundle>(bundlePathById);
}

}  // namespace react
}  // namespace facebook
