set ns [new Simulator]

set tr [open "file.tr" w]
$ns trace-all $tr

set nam [open "ani.nam" w]
$ns namtrace-all $nam

set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]



#$ns make-lan "$n1 $n2 $n3 $n4 $n5 $n6" 0.2Mb 20ms LL Queue/DropTail Mac/802_3  dsd - DropTail Mac/802_3


$ns duplex-link $n1 $n2 5Mb 10ms DropTail Mac/802_3
$ns duplex-link $n2 $n3 5Mb 10ms DropTail Mac/802_3
$ns duplex-link $n3 $n4 5Mb 10ms DropTail Mac/802_3
$ns duplex-link $n4 $n5 5Mb 10ms DropTail Mac/802_3
$ns duplex-link $n5 $n6 5Mb 10ms DropTail Mac/802_3

#$ns make-lan "$n1 $n2 $n3 $n4 $n5 $n6" 5Mb 10ms LL Queue/DropTail Mac/802_3

set tcp1 [new Agent/TCP]
set tcpc1 [new Agent/TCPSink]
$ns attach-agent $n1 $tcp1
$ns attach-agent $n6 $tcpc1
$ns connect $tcp1 $tcpc1
set app1 [new Application/FTP]
$app1 attach-agent $tcp1


set tcp2 [new Agent/TCP]
set tcpc2 [new Agent/TCPSink]
$ns attach-agent $n2 $tcp2
$ns attach-agent $n6 $tcpc2
$ns connect $tcp2 $tcpc2
set app2 [new Application/FTP]
$app2 attach-agent $tcp2

$ns at 0.5 "$app1 start"
$ns at 1.0 "$app2 start"
$ns at 9.0 "$app1 stop"
$ns at 9.5 "$app2 stop"

proc finish { } {
	global ns tr nam
	$ns flush-trace
	close $tr
	close $nam
	exit 0
}


$ns at 10.0 "finish"

$ns run



