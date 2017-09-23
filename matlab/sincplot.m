function [y]=sincplot(n)  
x1=0.01:0.01:n*pi;  
y1=sin(x1)./x1;  
x2=-n*pi:0.01:-0.01;  
y2=sin(x2)./x2;  
y=[y2 y1];  
plot([x2 x1], y);  