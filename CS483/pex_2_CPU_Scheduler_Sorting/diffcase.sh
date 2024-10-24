#!/bin/bash
gcc -Wall CPUs.c main.c processQueue.c CPUs.h processQueue.h -o pex2 -lpthread
./pex2 1 25 1 2 > sjf_1
./pex2 1 25 1 3 > pnp_1
./pex2 1 25 1 4 > rro_1
./pex2 1 25 1 5 > srt_1
./pex2 1 25 1 6 > ppp_1
./pex2 1 25 2 2 > sjf_2
./pex2 1 25 2 3 > pnp_2
./pex2 1 25 2 4 > rro_2
./pex2 1 25 2 5 > srt_2
./pex2 1 25 2 6 > ppp_2
./pex2 1 25 6 2 > sjf_6
./pex2 1 25 6 3 > pnp_6
./pex2 1 25 6 4 > rro_6
./pex2 1 25 6 5 > srt_6
./pex2 1 25 6 6 > ppp_6
./pex2 1 25 10 2 > sjf_10
./pex2 1 25 10 3 > pnp_10
./pex2 1 25 10 4 > rro_10
./pex2 1 25 10 5 > srt_10
./pex2 1 25 10 6 > ppp_10

diff sjf_1 ./pex2/sjf_1
diff pnp_1 ./pex2/pnp_1
diff rro_1 ./pex2/rro_1
diff srt_1 ./pex2/srt_1
diff ppp_1 ./pex2/ppp_1
diff sjf_2 ./pex2/sjf_2
diff pnp_2 ./pex2/pnp_2
diff rro_2 ./pex2/rro_2
diff srt_2 ./pex2/srt_2
diff ppp_2 ./pex2/ppp_2
diff sjf_6 ./pex2/sjf_6
diff pnp_6 ./pex2/pnp_6
diff rro_6 ./pex2/rro_6
diff srt_6 ./pex2/srt_6
diff ppp_6 ./pex2/ppp_6
diff sjf_10 ./pex2/sjf_10
diff pnp_10 ./pex2/pnp_10
diff rro_10 ./pex2/rro_10
diff srt_10 ./pex2/srt_10
diff ppp_10 ./pex2/ppp_10

