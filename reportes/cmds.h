pandoc -B portada.md reporte002.md -o archivo.pdf --pdf-engine=xelatex --toc --number-sections




pandoc mi_script.md -o mi_reporte.pdf --pdf-engine=pdflatex
julia -e 'using Literate; Literate.markdown(mi_script.jl, .; execute=false)'


pandoc -B portada.md reporte001.md reporte002.md reporte003.md -o archivo.pdf --pdf-engine=xelatex --toc --number-sections

//  con esto para gen report3:
//
pandoc -B portada.md reporte001.md reporte002.md reporte003.md -o archivo.pdf --pdf-engine=xelatex --toc --number-sections -H header.tex

//latest ya con biblio
pandoc -B portada.md reporte001.md reporte002.md reporte003.md -o archivo.pdf --pdf-engine=xelatex --toc --number-sections -H header.tex --citeproc --bibliography=refs.bib

pandoc -B portada.md  cap*.md -o archivo.pdf --pdf-engine=xelatex --toc --number-sections -H header.tex --citeproc --bibliography=refs.bib

//gen reporte3:
pandoc -B portada.md  cap*.md -o archivo.pdf --pdf-engine=xelatex --toc --number-sections -H header.tex --citeproc --bibliography=refs.bib --csl=ieee.csl
