from optparse import OptionParser
import os
import shutil
import sys

parser = OptionParser()
parser.add_option( "-p", "--project_path", dest = "project_path" )
parser.add_option( "-s", "--spn_path", dest = "spn_path" )
options, args = parser.parse_args()

spn_path = options.spn_path
project_path = options.project_path
project_name = os.path.basename( project_path )

# Create the .mkb file by walking the spn and project directories
# Marmalade uses the .mkb file to create the visual studio project
with open( project_name + ".mkb", "w+" ) as mkb_file:

	mkb_file.write( 
		"#!/usr/bin/env mkb\n" +
		"files\n" +
		"{\n"
	)

	def populate_from_directory( directory_path, ignored_paths = [], ignored_extensions = [] ):
		directory_base_name = os.path.basename( directory_path )
		for dirname, dirnames, filenames in os.walk( directory_path ):

			if os.path.basename( dirname ) in ignored_paths:
				continue

			if len( filenames ) > 0:
				relative_file_path = os.path.join( dirname, filenames[0] )[len( directory_path ) + 1:]
				project_filters = [ directory_base_name ] + relative_file_path.split( "\\" )[:-1]
				
				mkb_file.write(
					"\t(" + dirname + ")\n" +
					"\t[" + " ".join( project_filters ) + "]\n"
				)

				for filename in filenames:
					if filename.split(".")[1] not in ignored_extensions:
						mkb_file.write(
							"\t" + os.path.basename( filename ) + "\n"
						)

				mkb_file.write( "\n" )

	populate_from_directory( spn_path, ignored_extensions = [ "py", "pyc" ] )
	populate_from_directory( project_path, [ "fonts", "textures" ], [ "py", "pyc" ] )
	populate_from_directory( spn_path + "/../spn-marmalade" )

	mkb_file.write(
		"}\n" +
		"\n" +
		"subprojects\n" +
		"{\n"
			"\tiw2dscenegraph\n" +
		"}\n" +
		"\n"
	)

	mkb_file.write(
		"includepaths\n" +
		"{\n" +
			"\t" + spn_path + "/include\n" +
			"\t" + spn_path + "/../spn-marmalade" + "/include\n" +
			"\t" + project_path + "/include\n" +
			"\t" + project_path + "\n" +
		"}\n\n"
	)

	if os.path.exists( project_path + "defines.py" ):
		sys.path.append( project_path )		
		custom_define_module = __import__( "defines" )	
		sys.path.remove( project_path )
	
		if custom_define_module:
			custom_defines = custom_define_module.get_defines()

			mkb_file.write(
				"defines\n" + 
				"{\n"
			)

			for key, value in custom_defines.iteritems():
				mkb_file.write(
					"\t" + key + " = " + str( value ) + "\n"
				)

			mkb_file.write( "}\n" )

	assets_folder = project_path + "/assets"
	if os.path.isdir( assets_folder ):
		mkb_file.write(
			"assets\n" +
			"{\n" +
			"\t(data)\n"
		)

		for dirname, dirnames, filenames in os.walk( assets_folder ):

			if len( filenames  ) > 0:
				for filename in filenames:
					relative_file_path = os.path.join( dirname, filename )[len( assets_folder ) + 1:]
					mkb_file.write(
						"\t" + relative_file_path + "\n"
					)

			mkb_file.write( "\n" )

		mkb_file.write( 
			"}"
		)

		# Create data folder and copy assets over
		if not os.path.isdir( "data" ):
			os.mkdir( "data" )

		if os.path.isdir( "data" ):
			shutil.rmtree( "data" )

		shutil.copytree( assets_folder, "data" )