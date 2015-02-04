NS="1 2 4 8 16 32 64 128 256 512 1024"; # What to measure over
for n in $NS; do
    echo $n;
    /usr/bin/time -f %e cat /dev/zero | head -c 1000000 | ./passthrough $n > /dev/null
done
