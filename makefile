jdoc:
	cl /c jdoc.c
	cl /c formatting.c
	link jdoc.obj formatting.obj

clean: 
	del *.exe
	del *.asm
	del *.obj

# Student test
test:
	cl /c jdoc.c
	cl /c formatting.c
	link jdoc.obj formatting.obj
	jdoc -i Student.java -o Student_doc.txt

# Rectangle test
test2: 
	cl /c jdoc.c
	cl /c formatting.c
	link jdoc.obj formatting.obj
	jdoc -i Rectangle.java -o Rectangle_doc.txt