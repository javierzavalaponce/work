pandoc -B portada.md reporte002.md -o archivo.pdf --pdf-engine=xelatex --toc --number-sections




pandoc mi_script.md -o mi_reporte.pdf --pdf-engine=pdflatex
julia -e 'using Literate; Literate.markdown(mi_script.jl, .; execute=false)'


pandoc -B portada.md reporte001.md reporte002.md reporte003.md -o archivo.pdf --pdf-engine=xelatex --toc --number-sections


pandoc -B portada.md reporte001.md reporte002.md reporte003.md -o archivo.pdf --pdf-engine=xelatex --toc --number-sections -H header.tex
