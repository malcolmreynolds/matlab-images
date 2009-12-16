function draw3hist(hist,the_title)

plot(hist.lines{1}.x,hist.lines{1}.bins,'r');
hold on;
plot(hist.lines{2}.x,hist.lines{2}.bins,'g');
plot(hist.lines{3}.x,hist.lines{3}.bins,'b');
legend(hist.lines{1}.lab, hist.lines{2}.lab, hist.lines{3}.lab);
title(the_title);
hold off;
