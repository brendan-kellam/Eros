
#include "System/ResourceManager.h"


void CResourceManager::StartUp()
{
	
	/*char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	m_projectPath = std::string(buffer).substr(0, pos);*/


	wchar_t DllPath[MAX_PATH] = { 0 };
	GetModuleFileNameW((HINSTANCE)&__ImageBase, DllPath, _countof(DllPath));
	//m_projectPath = std::string(DllPath);
	char test[MAX_PATH];
	std::wcstombs(test, DllPath, MAX_PATH);
	m_projectPath = std::string(test);

	

}



void CResourceManager::ShutDown()
{ }

std::string CResourceManager::GetBaseProjectPath()
{
	return m_projectPath;
}

std::string CResourceManager::GetBaseResourcePath() 
{
	return GetBaseProjectPath() + "\\Resources";
}

std::string CResourceManager::GetResourcePath(std::string extension)
{
	return GetBaseProjectPath() + "\\" + extension;
}

std::string CResourceManager::GetShaderPath(std::string name)
{
	std::string temp = "Shaders\\" + name;
	return GetResourcePath(temp);
}




