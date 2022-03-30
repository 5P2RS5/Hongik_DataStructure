CC = gcc
PUB = /lab/theory/pub
HW = hw5

addr: addr.c backend-bst.o backend-bst.h
	${CC} -o addr addr.c backend-bst.o

backend-bst.o: backend-bst.c
	${CC} -c backend-bst.c

addr_demo: addr.c backend-bst_demo.o backend-bst.h
	${CC} -o addr_demo addr.c backend-bst_demo.o

addr-bst-ex: addr-bst-ex.c backend-bst_demo.c backend-bst.h
	${CC} -o addr-bst-ex addr-bst-ex.c backend-bst_demo.c

backend-bst_demo.o: backend-bst_demo.c
	${CC} -c backend-bst_demo.c

${HW}.zip: README.pdf addr.c backend-bst.c backend-bst.h Makefile check addr_demo
	chmod 755 addr_demo
	zip ${HW}.zip README.pdf addr.c backend-bst.c backend-bst.h Makefile test1.in ch_test1.out addr_demo

pub: ${HW}.zip
	cp ${HW}.zip ${PUB}/ds_hws/${HW}.zip
	chmod 644 ${PUB}/ds_hws/${HW}.zip

sync:
	rsync -rtv --delete . linux2.ce.hongik.ac.kr:hw/${HW}/ #timestamp preserving

test: addr
	./addr < test1.in > test1.out
	diff ch_test1.out test1.out

README.pdf: README.tex
	pdflatex README.tex

check: addr_demo test1.in
	./addr_demo < test1.in > ch_test1.out

clean: 
	rm addr addr_demo *.o ch_*.out *.aux *.log *.zip
