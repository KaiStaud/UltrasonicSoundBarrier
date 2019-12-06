function generate_keypair = crypto()
p = primes(0xFFFFFFFF);
q = primes(0xFFFFFFFF);

out(p);
out(q);
N = p*q;
out(N);
phi = (q-1) *(p-1);
out(phi);
end 
