reset

#default settings: set terminal svg size 600,480 fixed enhanced font 'Arial,12' butt dashlength 1.0
set terminal svg size 800,600 fixed enhanced font 'Arial,18' butt dashlength 1.0

set xlabel offset 0,1
set ylabel offset 2,0
set xtics offset 0,0.3

m = 1000

set xrange[1:2*m]; ext = ".1.svg"
#set xrange[1:m*m]; ext = ".2.svg"


set xlabel "n"
set ylabel "~G‾_n"

set key left top
#set key opaque

set arrow from m,graph 0 to m,graph 1 nohead dt 5 lw 2 lc "grey40"
set label "n = m" at m,graph 0 center front tc "grey40"

# d-choice schemes - online
set output "plots/online-d_m=".m.ext
plot "out/avgap_online_m=".m."_scheme=1_beta=0.000000.txt"  title "1-choice"       with lines lw 2,	\
     "out/avgap_online_m=".m."_scheme=0_beta=0.750000.txt"  title "(1+3/4)-choice" with lines lw 2,	\
     "out/avgap_online_m=".m."_scheme=0_beta=0.500000.txt"  title "(1+1/2)-choice" with lines lw 2,	\
     "out/avgap_online_m=".m."_scheme=0_beta=0.250000.txt"  title "(1+1/4)-choice" with lines lw 2,	\
     "out/avgap_online_m=".m."_scheme=2_beta=0.000000.txt"  title "2-choice"       with lines lw 2,	\
     "out/avgap_online_m=".m."_scheme=3_beta=0.000000.txt"  title "3-choice"       with lines lw 2,	\
     "out/avgap_online_m=".m."_scheme=4_beta=0.000000.txt"  title "4-choice"       with lines lw 2,	\
     "out/avgap_online_m=".m."_scheme=5_beta=0.000000.txt"  title "5-choice"       with lines lw 2,	\
     "out/avgap_online_m=".m."_scheme=10_beta=0.000000.txt" title "10-choice"      with lines lw 2

set output "plots/batched8m-d_m=".m.ext
plot "out/avgap_batched8m_m=".m."_scheme=1_beta=0.000000.txt"  title "1-choice"       with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=0_beta=0.750000.txt"  title "(1+3/4)-choice" with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=0_beta=0.500000.txt"  title "(1+1/2)-choice" with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=0_beta=0.250000.txt"  title "(1+1/4)-choice" with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=2_beta=0.000000.txt"  title "2-choice"       with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=3_beta=0.000000.txt"  title "3-choice"       with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=4_beta=0.000000.txt"  title "4-choice"       with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=5_beta=0.000000.txt"  title "5-choice"       with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=10_beta=0.000000.txt" title "10-choice"      with lines lw 2

# d-choice schemes - online vs batched (fixed d)

set output "plots/onlinesvbatched-d=2_beta_m=".m.ext
plot "out/avgap_online_m=".m."_scheme=2_beta=0.000000.txt"  title "b = 1"        with lines lw 2,	\
     "out/avgap_batched1m_m=".m."_scheme=2_beta=0.000000.txt"  title "b = m"     with lines lw 2,	\
     "out/avgap_batched2m_m=".m."_scheme=2_beta=0.000000.txt"  title "b = 2m"     with lines lw 2,	\
     "out/avgap_batched4m_m=".m."_scheme=2_beta=0.000000.txt"  title "b = 4m"     with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=2_beta=0.000000.txt"  title "b = 8m"     with lines lw 2,	\
     "out/avgap_batched16m_m=".m."_scheme=2_beta=0.000000.txt"  title "b = 16m"     with lines lw 2,	\
     "out/avgap_batched32m_m=".m."_scheme=2_beta=0.000000.txt"  title "b = 32m"     with lines lw 2, \
     "out/avgap_batched64m_m=".m."_scheme=2_beta=0.000000.txt"  title "b = 64m"     with lines lw 2, \
     "out/avgap_batched256m_m=".m."_scheme=2_beta=0.000000.txt"  title "b = 256m"     with lines lw 2, \
     "out/avgap_batched1024m_m=".m."_scheme=2_beta=0.000000.txt"  title "b = 1024m"     with lines lw 2, \
     "out/avgap_online_m=".m."_scheme=1_beta=0.000000.txt"  title "1-choice"       with lines lw 2


set output "plots/onlinesvbatched-d=5_beta_m=".m.ext
plot "out/avgap_online_m=".m."_scheme=5_beta=0.000000.txt"  title "b = 1"        with lines lw 2,	\
     "out/avgap_batched1m_m=".m."_scheme=5_beta=0.000000.txt"  title "b = m"     with lines lw 2,	\
     "out/avgap_batched2m_m=".m."_scheme=5_beta=0.000000.txt"  title "b = 2m"     with lines lw 2,	\
     "out/avgap_batched4m_m=".m."_scheme=5_beta=0.000000.txt"  title "b = 4m"     with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=5_beta=0.000000.txt"  title "b = 8m"     with lines lw 2,	\
     "out/avgap_batched16m_m=".m."_scheme=5_beta=0.000000.txt"  title "b = 16m"     with lines lw 2,	\
     "out/avgap_batched32m_m=".m."_scheme=5_beta=0.000000.txt"  title "b = 32m"     with lines lw 2, \
     "out/avgap_batched64m_m=".m."_scheme=5_beta=0.000000.txt"  title "b = 64m"     with lines lw 2, \
     "out/avgap_batched256m_m=".m."_scheme=5_beta=0.000000.txt"  title "b = 256m"     with lines lw 2, \
     "out/avgap_batched1024m_m=".m."_scheme=5_beta=0.000000.txt"  title "b = 1024m"     with lines lw 2, \
     "out/avgap_online_m=".m."_scheme=1_beta=0.000000.txt"  title "1-choice"       with lines lw 2

set output "plots/onlinesvbatched-d=10_beta_m=".m.ext
plot "out/avgap_online_m=".m."_scheme=10_beta=0.000000.txt"  title "b = 1"        with lines lw 2,	\
     "out/avgap_batched1m_m=".m."_scheme=10_beta=0.000000.txt"  title "b = m"     with lines lw 2,	\
     "out/avgap_batched2m_m=".m."_scheme=10_beta=0.000000.txt"  title "b = 2m"     with lines lw 2,	\
     "out/avgap_batched4m_m=".m."_scheme=10_beta=0.000000.txt"  title "b = 4m"     with lines lw 2,	\
     "out/avgap_batched8m_m=".m."_scheme=10_beta=0.000000.txt"  title "b = 8m"     with lines lw 2,	\
     "out/avgap_batched16m_m=".m."_scheme=10_beta=0.000000.txt"  title "b = 16m"     with lines lw 2,	\
     "out/avgap_batched32m_m=".m."_scheme=10_beta=0.000000.txt"  title "b = 32m"     with lines lw 2, \
     "out/avgap_batched64m_m=".m."_scheme=10_beta=0.000000.txt"  title "b = 64m"     with lines lw 2, \
     "out/avgap_batched256m_m=".m."_scheme=10_beta=0.000000.txt"  title "b = 256m"     with lines lw 2, \
     "out/avgap_batched1024m_m=".m."_scheme=10_beta=0.000000.txt"  title "b = 1024m"     with lines lw 2, \
     "out/avgap_online_m=".m."_scheme=1_beta=0.000000.txt"  title "1-choice"       with lines lw 2


# k-choice schemes - online (fixed d)

set output "plots/online-k-2_m=".m.ext
plot "out/avgap_online_partial_m=".m."_scheme=1questions-2bins.txt" title "1 question" with lines lw 2,	\
     "out/avgap_online_partial_m=".m."_scheme=2questions-2bins.txt" title "2 questions" with lines lw 2, \
     "out/avgap_online_m=".m."_scheme=2_beta=0.000000.txt"          title "∞ questions"        with lines lw 2

set output "plots/online-k-3_m=".m.ext
plot "out/avgap_online_partial_m=".m."_scheme=1questions-3bins.txt" title "1 question" with lines lw 2,	\
     "out/avgap_online_partial_m=".m."_scheme=2questions-3bins.txt" title "2 questions" with lines lw 2, \
     "out/avgap_online_m=".m."_scheme=3_beta=0.000000.txt"          title "∞ questions"        with lines lw 2

set output "plots/online-k-5_m=".m.ext
plot "out/avgap_online_partial_m=".m."_scheme=1questions-5bins.txt" title "1 question" with lines lw 2,	\
     "out/avgap_online_partial_m=".m."_scheme=2questions-5bins.txt" title "2 questions" with lines lw 2, \
     "out/avgap_online_m=".m."_scheme=5_beta=0.000000.txt"          title "∞ questions"        with lines lw 2

# k-choice schemes - batched (fixed d)

set output "plots/batched8m-k-2_m=".m.ext
plot "out/avgap_batched8m_partial_m=".m."_scheme=1questions-2bins.txt" title "1 question" with lines lw 2,	\
     "out/avgap_batched8m_partial_m=".m."_scheme=2questions-2bins.txt" title "2 questions" with lines lw 2, \
     "out/avgap_batched8m_m=".m."_scheme=2_beta=0.000000.txt"          title "∞ questions"        with lines lw 2

set output "plots/batched8m-k-3_m=".m.ext
plot "out/avgap_batched8m_partial_m=".m."_scheme=1questions-3bins.txt" title "1 question" with lines lw 2,	\
     "out/avgap_batched8m_partial_m=".m."_scheme=2questions-3bins.txt" title "2 questions" with lines lw 2, \
     "out/avgap_batched8m_m=".m."_scheme=3_beta=0.000000.txt"          title "∞ questions"        with lines lw 2

set output "plots/batched8m-k-5_m=".m.ext
plot "out/avgap_batched8m_partial_m=".m."_scheme=1questions-5bins.txt" title "1 question" with lines lw 2,	\
     "out/avgap_batched8m_partial_m=".m."_scheme=2questions-5bins.txt" title "2 questions" with lines lw 2, \
     "out/avgap_batched8m_m=".m."_scheme=5_beta=0.000000.txt"          title "∞ questions"        with lines lw 2

# k-choice schemes - online (fixed k)

set output "plots/online-k=1_m=".m.ext
plot "out/avgap_online_partial_m=".m."_scheme=1questions-2bins.txt" title "2 choices" with lines lw 2,	\
     "out/avgap_online_partial_m=".m."_scheme=1questions-3bins.txt" title "3 choices" with lines lw 2,	\
     "out/avgap_online_partial_m=".m."_scheme=1questions-5bins.txt" title "5 choices" with lines lw 2

set output "plots/online-k=2_m=".m.ext
plot "out/avgap_online_partial_m=".m."_scheme=2questions-2bins.txt" title "2 choices" with lines lw 2,	\
     "out/avgap_online_partial_m=".m."_scheme=2questions-3bins.txt" title "3 choices" with lines lw 2,	\
     "out/avgap_online_partial_m=".m."_scheme=2questions-5bins.txt" title "5 choices" with lines lw 2

# k-choice schemes - per k - batched

set output "plots/batched8m-k=1_m=".m.ext
plot "out/avgap_batched8m_partial_m=".m."_scheme=1questions-2bins.txt" title "2 choices" with lines lw 2,	\
     "out/avgap_batched8m_partial_m=".m."_scheme=1questions-3bins.txt" title "3 choices" with lines lw 2,	\
     "out/avgap_batched8m_partial_m=".m."_scheme=1questions-5bins.txt" title "5 choices" with lines lw 2

set output "plots/batched8m-k=2_m=".m.ext
plot "out/avgap_batched8m_partial_m=".m."_scheme=2questions-2bins.txt" title "2 choices" with lines lw 2,	\
     "out/avgap_batched8m_partial_m=".m."_scheme=2questions-3bins.txt" title "3 choices" with lines lw 2,	\
     "out/avgap_batched8m_partial_m=".m."_scheme=2questions-5bins.txt" title "5 choices" with lines lw 2
