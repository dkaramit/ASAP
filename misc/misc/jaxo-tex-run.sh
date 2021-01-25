latex $1.tex ; dvips $1.dvi ; rm $1.dvi ; rm $1.log ; rm $1.aux; ps2pdf $1.ps ; rm $1.ps; pdfcrop $1.pdf $1.pdf; 
pdftoppm -png $1.pdf > $1.png
rm $1.pdf