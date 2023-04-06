# MP3-tag-reader-and-Editor
MP tag reader &amp; editor: Effortlessly manage &amp; edit multimedia metadata. Batch edit, auto-tag, support multiple file formats. Organize your music &amp; video files with ease! #MPtagreader #metadataeditor
1. Files in the directory are
	* Main.c  - This file contains main function.
	* types.h - This file contains all return type enums.
	* view.h  - This file contains all function declarations for viewing.
	* Edit.h  - This file contains all function declarations for Editing.
	* view.c  - This is the file containing all the function definitions for viewing.
	* Edit.c  - This is the file containing all the function definitions for editing.
2. Open the terminal and execute all the files inorder to generate an executable file.
3. Run the executable file with the arguments as shown
   To view-
      <executable file name> -v <MP3 file name>
   To Edit-
      <executable file name> -e -[taAyc] <Edit value> <MP3 file name>
		-t      Modifies a Title tag
		-a      Modifies a Artist tag
		-A      Modifies a Album tag
		-y      Modifies a Year tag
		-c      Modifies a Comment tag
   For help-
      <executable file name> --h
