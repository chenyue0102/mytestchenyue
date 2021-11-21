// testvulkan.cpp: 定义应用程序的入口点。
//

#include "testvulkan.h"
#include <vector>
#include <stdint.h>
#include <assert.h>
#include <vulkan/vulkan.h>

using namespace std;

struct LayerProperties {
	VkLayerProperties properties;
	std::vector<VkExtensionProperties> extensions;
};

std::vector< LayerProperties> getLayerAndExtension() {
	uint32_t instanceLayerCount = 0;
	VkResult res;
	std::vector<VkLayerProperties> layerProperties;
	res = vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
	assert(res == VK_SUCCESS);
	layerProperties.resize(instanceLayerCount);
	res = vkEnumerateInstanceLayerProperties(&instanceLayerCount, layerProperties.data());
	assert(res == VK_SUCCESS);

	std::vector< LayerProperties> layerPropertyList;
	for (auto& layer : layerProperties) {
		LayerProperties layerProp;
		layerProp.properties = layer;

		uint32_t extensionCount = 0;
		res = vkEnumerateInstanceExtensionProperties(layer.layerName, &extensionCount, nullptr);
		assert(res == VK_SUCCESS);
		layerProp.extensions.resize(extensionCount);
		vkEnumerateInstanceExtensionProperties(layer.layerName, &extensionCount, layerProp.extensions.data());
		layerPropertyList.push_back(layerProp);
	}
	return layerPropertyList;
}


int main()
{
	std::vector< LayerProperties> layerPropertyList = getLayerAndExtension();
	VkInstance instance = 0;

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = 0;
	appInfo.pApplicationName = "Hello,Vulkan";
	appInfo.pEngineName = appInfo.pApplicationName;
	appInfo.engineVersion = 1;
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instInfo = {};
	instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instInfo.pNext = 0;
	instInfo.flags = 0;
	instInfo.pApplicationInfo = &appInfo;

	VkResult res = vkCreateInstance(&instInfo, nullptr, &instance);
	cout << "Hello CMake." << " res:" << res << endl;

	vkDestroyInstance(instance, nullptr);
	return 0;
}
