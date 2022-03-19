#pragma once
#include <string_view>

constexpr std::wstring_view HelpText{
	LR"(commandline arguments:
	path=<path>
		optional argument that gives a root directory. if this is not supplied then the root directory is the current working directory.
	recursive
		option argument that tells the application to modify all files that fit the filter in all directories recursivly
	filename=<filename>
		the filename to do the action on. cannot be a commandline argument if filter is.
	filter=<filterRegex>
		cannot be a commandline argument if filename is.
	action=<list|modify>
		list=list the metadata keys and values for the given <filename> or <filter>
		modify=modify the metadata keys and values for the given <filename> or <filter>
	key=<keyname>
		the key string to modify for the given <filename> or files that match <filter>. keys can be listed by action=list.
	value=<valuestring>
		what to change the value of the given key to.
	propertygroup=<basic|attribute|music|video|document>
	type=<>
		when the key doesnt exist in the file, we need to know what the type of the new metadata key is going to be.
Examples:
	ModMeta.exe filename="example.mp3" path="c:\music" action=list
		list the metadata keys and values for the file c:\music\example.mp3
	ModMeta.exe filter=".*\.mp3" action=modify key=author value="Myself"
		for all files in the working directory that match the regex ".*\.mp3", modify the author metadata to say "myself"
)"
};