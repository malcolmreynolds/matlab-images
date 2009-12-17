function draw3hist_old(bins,the_title)
 
figure;
plot(bins.r,'r');
hold on;
plot(bins.g,'g');
plot(bins.b,'b');
hold off;
title(the_title);