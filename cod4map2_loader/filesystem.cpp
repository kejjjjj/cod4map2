#include "h.h"


std::string F::F_GetFileExtension(std::string file)
{

	int extensionPos = file.find_last_of(".");

	if (extensionPos < 0)
		return "No extension";

	file = file.substr(extensionPos);


	return file;
}
std::string F::F_removeFileExtension(std::string file, size_t chars)
{
	return file.substr(0, file.size() - chars);
}
std::string F::F_GetFileName(std::string path)
{
	int pos = path.find_last_of("\\");

	if (pos < 0)
		return path;

	return path.substr(pos + 1);
}
void F::F_GoToPreviousDirectory(std::string* directory)
{
	size_t pos = directory->find_last_of('\\');

	if (pos > 0)
		*directory = directory->substr(0, pos);
}
std::string F::F_GoToPreviousDirectory(std::string directory)
{
	size_t pos = directory.find_last_of('\\');
	if (pos < 1)
		return directory;

	return directory.substr(0, pos);
}
template<typename t>
void F::F_FilesInThisDirectory(std::string directory, std::vector<t>* out)
{
	U::vecReset<std::string>(&(*out), 4096);
	int i{ 0 };
	if (!fs::exists(directory)) {
		return;
	}
	for (const auto& entry : fs::directory_iterator(directory)) {
		if (entry.is_regular_file()) {
			out->push_back(entry.path().string());
			i += 1;
		}
	}
	out->resize(i);
}
bool F::F_FileBelongsToThisDirectory(std::string directory, std::string file)
{
	std::vector<std::string> thisdir;
	F_FilesInThisDirectory(directory, &thisdir);

	for (size_t i = 0; i < thisdir.size(); i++) {
		if (thisdir[i] == file)
			return true;
	}
	
	return false;
}
std::string F::F_GetExeFileName()
{
	char buffer[260];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}
std::string F::F_GetExePath()
{
	std::string f = F_GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}