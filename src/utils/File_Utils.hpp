/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <set>
#include <string>
#include <vector>

#include <filesystem>
#include <optional>

#ifdef CopyFile
#undef CopyFile
#endif

namespace FileUtils {

std::string GetCurrentFolder();

bool FileExists(const std::string& folderPath);
bool FolderExists(const std::string& folderPath);

std::vector<std::string> ListFolderFiles(
    const std::string folder,
    const std::set<std::string>& matchExtensions);

bool CreatePath(std::string path);

bool CopyFile(
    const std::string& srcFilename,
    const std::string& dstFilename,
    bool createPath = false);

inline std::string GetAbsolutePath(const std::string& filePath) {
  return std::filesystem::absolute(filePath).string();
}

inline std::string GetCurrentFolder() {
  return std::filesystem::current_path().string();
}

inline bool FileExists(const std::string& filePath) {
  return std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath);
}

inline bool FolderExists(const std::string& folderPath) {
  return std::filesystem::exists(folderPath) && std::filesystem::is_directory(folderPath);
}

inline std::string getFolder(const std::string& path) {
  auto parent = std::filesystem::path(path).parent_path().string();
  return parent == "" ? "." : parent;
}

inline std::string GetFileName(const std::string& path) {
  return std::filesystem::path(path).filename().string();
}

inline std::string GetFileBase(const std::string& path) {
  return std::filesystem::path(path).stem().string();
}

inline std::optional<std::string> GetFileSuffix(const std::string& path) {
  const auto& extension = std::filesystem::path(path).extension();
  if (extension.empty()) {
    return {};
  }
  return extension.string().substr(1);
}

inline bool MakeDir(const std::string& path) {
  return std::filesystem::create_directories(std::filesystem::path(path));
}

} // namespace FileUtils
