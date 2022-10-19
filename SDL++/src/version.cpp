#include "version.hpp"

using namespace SDL;

Version::Version(Uint8 major, Uint8 minor, Uint8 patch) { this->major = major, this->minor = minor, this->patch = patch; }
Version::Version(const SDL_version& v) { *this = v; }

Uint16 Version::AsNum() const { return SDL_VERSIONNUM(major, minor, patch); }

bool Version::Atleast() const { return SDL_VERSION_ATLEAST(major, minor, patch); }

Version GetVersion() {
	Version ver;
	SDL_GetVersion(&ver);
	return ver;
}

const char* GetRevision() { return SDL_GetRevision(); }
