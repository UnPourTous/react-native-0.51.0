// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include <cxxreact/RAMBundleRegistry.h>

namespace facebook {
namespace react {

class JSUnBundleSdCardRegistry: public RAMBundleRegistry {
public:
  JSUnBundleSdCardRegistry(std::unique_ptr<JSModulesUnbundle> mainBundle, const std::string& baseDirectoryPath);

protected:
  virtual std::unique_ptr<JSModulesUnbundle> bundleById(uint32_t index) const override;
private:
  std::string m_baseDirectoryPath;
};

}  // namespace react
}  // namespace facebook
