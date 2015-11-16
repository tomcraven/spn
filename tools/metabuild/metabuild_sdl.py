from optparse import OptionParser
import os
import shutil
import sys
import glob
import re

parser = OptionParser()
parser.add_option( "-p", "--project_path", dest = "project_path" )
parser.add_option( "-s", "--spn_path", dest = "spn_path" )
options, args = parser.parse_args()

spn_path = options.spn_path
project_path = options.project_path
project_name = os.path.basename( project_path )

uid = 0
def generate_uid():
	global uid
	uid += 1
	return "00000000-0000-0000-0000-" + str( uid ).zfill( 12 )

project_uid = generate_uid()
with open( project_name + ".sln", "w+" ) as solution_file:
	solution_file.write( \
"""Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Express 2013 for Windows Desktop
VisualStudioVersion = 12.0.30723.0
MinimumVisualStudioVersion = 10.0.40219.1
Project("{0}") = "{1}", "{1}/{1}.vcxproj", "{2}"
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|Win32 = Debug|Win32
		Release|Win32 = Release|Win32
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{2}.Debug|Win32.ActiveCfg = Debug|Win32
		{2}.Debug|Win32.Build.0 = Debug|Win32
		{2}.Release|Win32.ActiveCfg = Release|Win32
		{2}.Release|Win32.Build.0 = Release|Win32
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
EndGlobal""".format( generate_uid(), project_name, project_uid ) )

if not os.path.isdir( project_name ):
	os.mkdir( project_name )

with open( project_name + "/" + project_name + ".vcxproj", "w+" ) as project_file:

	sdl_include_path = "../" + spn_path + "/../external/libs/SDL/include"
	sdl_lib_path = spn_path + "/../external/libs/SDL/lib/x86"
	sdl_lib = "../" + sdl_lib_path + "/SDL2.lib"
	sdl_main_lib = "../" + sdl_lib_path + "/SDL2main.lib"

	sdl_ttf_include_path = "../" + spn_path + "/../external/libs/SDL2_ttf/include"
	sdl_ttf_lib_path = spn_path + "/../external/libs/SDL2_ttf/lib/x86"
	sdl_ttf_lib = "../" + sdl_ttf_lib_path + "/SDL2_ttf.lib"

	sdl_image_include_path = "../" + spn_path + "/../external/libs/SDL_image/include"
	sdl_image_lib_path = spn_path + "/../external/libs/SDL_image/lib/x86"
	sdl_image_lib = "../" + sdl_image_lib_path + "/SDL2_image.lib"

	project_include_directory = "../" + project_path + "/include"
	spn_include_directory = "../" + spn_path + "/include"
	spn_sdl_include_directory = "../" + spn_path + "/../spn-sdl/include"

  	include_directories = ";".join( \
		[ 
			sdl_include_path, 
			project_include_directory, 
			spn_include_directory, 
			spn_sdl_include_directory,
			sdl_image_include_path,
			sdl_ttf_include_path
		]
	)

	project_file.write( \
"""<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" ToolsVersion="12.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
	<ProjectConfiguration Include="Debug|Win32">
	  <Configuration>Debug</Configuration>
	  <Platform>Win32</Platform>
	</ProjectConfiguration>
	<ProjectConfiguration Include="Release|Win32">
	  <Configuration>Release</Configuration>
	  <Platform>Win32</Platform>
	</ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
	<ProjectGuid>{0}</ProjectGuid>
	<TargetFrameworkVersion>v4.5</TargetFrameworkVersion>
	<Keyword>ManagedCProj</Keyword>
	<RootNamespace>sdl_test</RootNamespace>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
	<ConfigurationType>Application</ConfigurationType>
	<UseDebugLibraries>true</UseDebugLibraries>
	<PlatformToolset>v120</PlatformToolset>
	<CLRSupport>true</CLRSupport>
	<CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
	<ConfigurationType>Application</ConfigurationType>
	<UseDebugLibraries>false</UseDebugLibraries>
	<PlatformToolset>v120</PlatformToolset>
	<CLRSupport>true</CLRSupport>
	<CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
	<Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
	<Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
	<LinkIncremental>true</LinkIncremental>
	<ExecutablePath>$(ExecutablePath)</ExecutablePath>
	<IncludePath>{1};$(IncludePath)</IncludePath>
	<OutDir>$(ProjectDir)$(Configuration)\</OutDir>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
	<LinkIncremental>false</LinkIncremental>
	<ExecutablePath>$(ExecutablePath)</ExecutablePath>
	<IncludePath>{1};$(IncludePath)</IncludePath>
	<OutDir>$(ProjectDir)$(Configuration)\</OutDir>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
	<ClCompile>
	  <WarningLevel>Level3</WarningLevel>
	  <Optimization>Disabled</Optimization>
	  <PreprocessorDefinitions>WIN32;_DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
	  <RuntimeLibrary>MultiThreadedDebugDLL</RuntimeLibrary>
	</ClCompile>
	<Link>
	  <GenerateDebugInformation>true</GenerateDebugInformation>
	  <AdditionalDependencies>
	  </AdditionalDependencies>
	  <AdditionalLibraryDirectories>
	  </AdditionalLibraryDirectories>
	  <SubSystem>Console</SubSystem>
	</Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
	<ClCompile>
	  <WarningLevel>Level3</WarningLevel>
	  <PreprocessorDefinitions>WIN32;NDEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
	  <RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>
	</ClCompile>
	<Link>
	  <GenerateDebugInformation>true</GenerateDebugInformation>
	  <AdditionalDependencies>
	  </AdditionalDependencies>
	  <AdditionalLibraryDirectories>
	  </AdditionalLibraryDirectories>
	  <SubSystem>Console</SubSystem>
	</Link>
  </ItemDefinitionGroup>
  <ItemGroup>
""".format( project_uid, include_directories ) )

	def populate_from_directory( directory, ignored_directories = [] ):

		dirname_prefix = os.path.basename( os.path.normpath( directory ) )

		for dirname, dirnames, filenames in os.walk( directory ):

			found = False
			for directory in ignored_directories:
				if directory in dirname:
					found = True
					break
			if found:
				continue

			for filename in filenames:
				extension = os.path.splitext( filename )[1]
				if extension == ".cpp":
					project_file.write( "    <ClCompile Include=\"../" + dirname + "/" + filename + "\" />\n" )
				else:
					project_file.write( "    <ClInclude Include=\"../" + dirname + "/" + filename + "\" />\n" )

	populate_from_directory( spn_path )
	populate_from_directory( spn_path + "/../spn-sdl" )
	populate_from_directory( project_path, [ "assets" ] )

	project_file.write( \
  """</ItemGroup>
  <ItemGroup>
	<Library Include="{0}" />
	<Library Include="{1}" />
	<Library Include="{2}" />
	<Library Include="{3}" />
  </ItemGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>""".format( sdl_lib, sdl_main_lib, sdl_image_lib, sdl_ttf_lib ) )

with open( project_name + "/" + project_name + ".vcxproj.user", "w+" ) as project_user_file:
	project_user_file.write( \
"""<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="12.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <LocalDebuggerWorkingDirectory>$(ProjectDir)/$(Configuration)</LocalDebuggerWorkingDirectory>
    <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <LocalDebuggerWorkingDirectory>$(ProjectDir)/$(Configuration)</LocalDebuggerWorkingDirectory>
    <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
  </PropertyGroup>
</Project>""" )

with open( project_name + "/" + project_name + ".vcxproj.filters", "w+" ) as project_filters_file:
	project_filters_file.write( \
"""<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup>""")

	cachedFilters = []

	def populate_from_directory( directory, ignored_directories = [] ):

		dirname_prefix = os.path.basename( os.path.normpath( directory ) )

		for dirname, dirnames, filenames in os.walk( directory ):

			found = False
			for directory in ignored_directories:
				if directory in dirname:
					found = True
					break
			if found:
				continue

			remaining_file_path = dirname[ dirname.rfind( dirname_prefix ): ]

			for filename in filenames:
				folderFilter = re.split("\\\\|/", remaining_file_path )
				folderFilter = "\\".join( folderFilter )
				cachedFilters.append( folderFilter )

				filename = "../" + dirname + "/" + filename

				tag = "ClInclude"
				extension = os.path.splitext( filename )[1]
				if extension == ".cpp":
					tag = "ClCompile"

				project_filters_file.write( \
"""    <{2} Include="{0}">
      <Filter>{1}</Filter>
    </{2}>
""".format( filename, folderFilter, tag ) )

	populate_from_directory( spn_path )
	populate_from_directory( spn_path + "/../spn-sdl" )
	populate_from_directory( project_path, [ "assets" ] )

	newFolderFilters = [ x for x in cachedFilters ]
	for folderFilter in cachedFilters:
		splitFilters = folderFilter.split( "\\" )
		runningFilter = splitFilters[0]
		for f in splitFilters[1:]:
			newFolderFilters.append( runningFilter )
			runningFilter += "\\" + f

	cachedFilters = newFolderFilters

	for folderFilter in list( set( cachedFilters ) ):
		project_filters_file.write( \
"""  </ItemGroup>
  <ItemGroup>
    <Filter Include="{0}">
      <UniqueIdentifier>{1}</UniqueIdentifier>
    </Filter>
""".format( folderFilter, generate_uid() ) )

	project_filters_file.write( \
"""  </ItemGroup>
</Project>
""" )

# copy sdl.dll to debug/release directories
if not os.path.isdir( project_name + "/Debug" ):
	os.mkdir( project_name + "/Debug" )
if not os.path.isdir( project_name + "/Release" ):
	os.mkdir( project_name + "/Release" )

shutil.copy( sdl_lib_path + "/SDL2.dll", project_name + "/Debug/" )
shutil.copy( sdl_lib_path + "/SDL2.dll", project_name + "/Release/" )

for filename in glob.glob(sdl_image_lib_path + "/*.dll"):
	shutil.copy( filename, project_name + "/Debug/" )
	shutil.copy( filename, project_name + "/Release/" )

for filename in glob.glob(sdl_ttf_lib_path + "/*.dll"):
	shutil.copy( filename, project_name + "/Debug/" )
	shutil.copy( filename, project_name + "/Release/" )

assets_folder = project_path + "/assets"

import distutils.dir_util
distutils.dir_util.copy_tree( assets_folder, project_name + "/Debug/" )
distutils.dir_util.copy_tree( assets_folder, project_name + "/Release/" )