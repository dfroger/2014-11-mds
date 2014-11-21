force:
	pdflatex -shell-escape ci.tex
#pdflatex --interaction=nonstopmode -shell-escape data_format.tex

visu:
	evince data_format.pdf &

clean:
	rm -rf *.aux *.log *.nav *.out *.snm *.toc ci.pdf
