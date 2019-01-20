function y = filter_no_recursive(in, b)
    y = zeros(size(in));    
    y(1)=b(1)*in(1);
    y(2)= b(1)*in(2) + b(2) * in(1);
    
    for n = 4:1:length(in)
     y(n)=b(1)*in(n)+b(2)*in(n-1)+b(3)*in(n-2)+b(4)*in(n-3);
    end
end