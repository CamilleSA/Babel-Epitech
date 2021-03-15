from conans import ConanFile, CMake

class Babel(ConanFile):
	requires = \
		"boost/1.71.0", \
		"sqlite_orm/1.5@bincrafters/stable", \
		"qt/5.14.2@bincrafters/stable", \
		"portaudio/v190600.20161030@bincrafters/stable", \
		"opus/1.3.1@bincrafters/stable", \
		"sqlite3/3.32.3"
	generators = "cmake"
	build_policy = "always"
