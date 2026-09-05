#!/bin/sh
set -e

# TODO: Windows x86 and Darwin support

# Environment setup
# VulkanSDK
PROJECT_VK_SDK_VERSION="1.4.357.0"

if [ -f "$(dirname "$0")/lib/vulkanSDK/$PROJECT_VK_SDK_VERSION/setup-env.sh" ]; then
  . "$(dirname "$0")/lib/vulkanSDK/$PROJECT_VK_SDK_VERSION/setup-env.sh"
fi

if [ -n "$VULKAN_SDK" ]; then
  export VK_SDK_BASE_DIR="$(dirname "$(dirname "$VULKAN_SDK")")"
  if [ -d "$VK_SDK_BASE_DIR/$PROJECT_VK_SDK_VERSION" ]; then
    echo "Using Vulkan SDK version $PROJECT_VK_SDK_VERSION at $VK_SDK_BASE_DIR"
  else
    echo "Vulkan SDK Version $(basename $(dirname "$VULKAN_SDK")) installed does not match the physics-engine's required LunarG Vulkan SDK version $PROJECT_VK_SDK_VERSION"
  fi
else
  echo "VulkanSDK environment is not setup. If you the SDK installed in another location, run setup-env.sh provided by the SDK. Otherwise, would you like to automatically install the required LunarG VulkanSDK inside the source? [y/N]"
  read choice
  case "$choice" in
  [Yy] | [Yy][Ee][Ss])
    echo "Installing Vulkan SDK.."
    VK_DOWNLOAD_URL="https://sdk.lunarg.com/sdk/download/${PROJECT_VK_SDK_VERSION}/linux/vulkansdk-linux-x86_64-${PROJECT_VK_SDK_VERSION}.tar.xz"
    mkdir "$(dirname "$0")/tmp"
    wget -O "$(dirname "$0")/tmp/sdk.tar.xz" "$VK_DOWNLOAD_URL"
    mkdir -p "$(dirname "$0")/lib/vulkanSDK"
    tar -xf "$(dirname "$0")/tmp/sdk.tar.xz" --directory "$(dirname "$0")/lib/vulkanSDK"
    ;;
  *)
    echo "Aborting.."
    ;;
  esac
fi

cmake --preset release --fresh
cmake --build --preset release
