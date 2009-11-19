function draw3hist(bins,the_title)

figure;
plot(bins{1},'r');
hold on;
plot(bins{2},'g');
plot(bins{3},'b');
hold off;
title(the_title);