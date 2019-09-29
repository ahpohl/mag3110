set datafile separator ","
set terminal png size 900,400
set title "Gasmeter"
#set xdata time
#set timefmt "%s"
#set format x "%H:%M"
#set xlabel "Time (hh:mm)"
set ylabel "Volume (m^3)"
set key top left
set grid
set xrange [13200:13300]
plot "mag.txt" using 1 with lines lw 2 lt 2 lc rgb "black" title 'Sum' , \
"mag.txt" using 2 with lines lw 2 lt 2 lc rgb "red" title 'x-axis', \
"mag.txt" using 3 with lines lw 2 lt 2 lc rgb "blue" title 'y-axis', \
"mag.txt" using 4 with lines lw 2 lt 2 lc rgb "cyan" title 'z-axis'
