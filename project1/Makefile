
# Default target

all: meme crop bw colorshift overlay

#build meme executable

meme: meme.o simp.o act.o fsf.o mem.o utility.o
	gcc -ansi -pedantic -o meme meme.o simp.o act.o fsf.o mem.o utility.o

# build crop executable 

crop: crop.o simp.o
	gcc -ansi -pedantic -o crop crop.o simp.o
	
# build bw executable 

bw: bw.o simp.o
	gcc -ansi -pedantic -o bw bw.o simp.o
	
# build colorshift executable 

colorshift: colorshift.o simp.o
	gcc -ansi -pedantic -o colorshift colorshift.o simp.o

# build overlay executable 

overlay: overlay.o simp.o
	gcc -ansi -pedantic -o overlay overlay.o simp.o
	
# build meme object file

meme.o: meme.c simp.h act.h mem.h fsf.h
	gcc -ansi -pedantic -c meme.c
	
# build crop object file

crop.o: crop.c simp.h
	gcc -ansi -pedantic -c crop.c
	
# build bw object file

bw.o: bw.c simp.h
	gcc -ansi -pedantic -c bw.c

# build colorshift object file

colorshift.o: colorshift.c simp.h
	gcc -ansi -pedantic -c colorshift.c
	
# build overlay object file

overlay.o: overlay.c simp.h
	gcc -ansi -pedantic -c overlay.c

# build simp object file	

simp.o: simp.c simp.h
	gcc -ansi -pedantic -c simp.c
	
# build act object file
	
act.o: act.c act.h utility.h
	gcc -ansi -pedantic -c act.c

# build fsf object file

fsf.o: fsf.c fsf.h utility.h
	gcc -ansi -pedantic -c fsf.c

# build mem object file

mem.o: mem.c mem.h utility.h
	gcc -ansi -pedantic -c mem.c
	
# build utility object file
	
utility.o: utility.c utility.h
	gcc -ansi -pedantic -c utility.c

# remove object files and executables

clean:
	touch crop.o bw.o colorshift.o overlay.o simp.o meme.o act.o fsf.o mem.o utility.o crop bw colorshift overlay meme; rm crop.o bw.o colorshift.o overlay.o simp.o meme.o act.o fsf.o mem.o utility.o crop bw colorshift overlay meme
	
acole6.tar.gz: Makefile crop.c bw.c colorshift.c overlay.c simp.c meme.c act.c fsf.c mem.c utility.c simp.h act.h fsf.h mem.h utility.h README
	tar -czf acole6.tar.gz Makefile crop.c bw.c colorshift.c overlay.c simp.c meme.c act.c fsf.c mem.c utility.c simp.h act.h fsf.h mem.h utility.h README		
