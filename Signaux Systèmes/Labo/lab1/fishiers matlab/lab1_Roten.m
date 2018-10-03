%point 3.1
%déclaration des variables
f = 1000
tau=1e-3
t = (-2:1e-6:9);
u=heaviside(t);

%afficher le signal x1
x1=cos(2*pi*f*t);
subplot(3,1,1)

plot(t*1e3,x1,'blue')
xlim([-2 9])
ylim([-1 1])
xlabel('t[ms]')
ylabel('X_1(t)')

%afficher le signal x2
x2=cos(2*pi*f*t).*u;
subplot(3,1,2)

plot(t*1e3,x2,'r')
xlim([-2 9])
ylim([-1 1])
xlabel('t[ms]')
ylabel('X_2(t)')

%afficher le signal x3
u=heaviside(t);
x3=exp(-t/tau).*cos(2*pi*f*t).*u;
subplot(3,1,3)
plot(t*1e3,x3,'k')
xlim([-2 9])
ylim([-1 1])
xlabel('t[ms]')
ylabel('X_3(t)')

%%
%Point 3.2

%déclaration des variables
f = 2
t = (-1:1e-6:1);
%signal x1
x1=sin(2*pi*f*t)+1/3*sin(2*pi*3*f*t)+1/5*sin(2*pi*5*f*t)+1/7*sin(2*pi*7*f*t)+1/9*sin(2*pi*9*f*t);
plot(t,x1,'r');
hold on
%signal x2
x2=cos(2*pi*f*t)+1/3^2*cos(2*pi*3*f*t)+1/5^2*cos(2*pi*5*f*t)+1/7^2*cos(2*pi*7*f*t)+1/9^2*cos(2*pi*9*f*t);
plot(t,x2,'b');
xlabel('t[s]')



%%
%Point 3.3

%déclaration des variables
f = 2;
t = (-1:1e-6:1);
%signal x1
x1=sin(2*pi*f*t)+1/3*sin(2*pi*3*f*t)+1/5*sin(2*pi*5*f*t)+1/7*sin(2*pi*7*f*t)+1/9*sin(2*pi*9*f*t);
y=fft(x1);
%signal x2
x2=cos(2*pi*f*t)+1/3^2*cos(2*pi*3*f*t)+1/5^2*cos(2*pi*5*f*t)+1/7^2*cos(2*pi*7*f*t)+1/9^2*cos(2*pi*9*f*t);
xlabel('t[s]')
z=fft(x2);
% plot(t,y);
plot(abs(z),'black');
hold on
plot(abs(y),'r');








