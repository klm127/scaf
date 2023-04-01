#ifdef _WIN32
#include <windows.h>
#elif
#include <unistd.h>
#endif 

#include <filesystem>
#include <Config.h>

/*!
    GetFullExePath is used to get the actual fs location of scaf. This is different from where the current working directory is. It's often referred to as the process working directory. Apparently pwd functions are not cross-platform in the built-in libraries, so directives are used to make scaf compatible on linux and windows. 

    This is used to locate scaf's config in the same directory as scaf. 

    \returns The folder containing scaf. 

    From https://stackoverflow.com/questions/50889647/best-way-to-get-exe-folder-path
*/
fs::path GetFullExePath() {

#ifdef _WIN32
    wchar_t a_path[MAX_PATH];
    GetModuleFileNameW(NULL, a_path, MAX_PATH);
#else
    char a_path[PATH_MAX];
    ssize_t count = readLink( "/proc/self/exe" , a_path, PATH_MAX);
    szPath[count] = '\0';
#endif 

    return fs::path{ a_path }.parent_path();
}
