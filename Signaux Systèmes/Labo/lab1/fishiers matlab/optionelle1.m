function out = optionelle1(nb)
x=1;
tempo =0;
f = 2;
t = (-1:1e-6:1);

for i=-1:1:(nb-1)
    x1=(1/x)*sin(2*pi*x*f*t);
    x= x+2;
    tempo = tempo+x1;
end
out = tempo;
end
