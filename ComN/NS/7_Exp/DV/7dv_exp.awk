BEGIN {
	recvdSize = 0
	startTime = 0.5
	stopTime = 5.0
}

{
	
	if ($1 == "s") {
		if ($2 < startTime) {
			startTime = $2
		}
	}

	if ($1 == "r") {
		if ($2 > stopTime) {
			stopTime = $2
		}
		
		recvdSize += $6
	}

}

END {

	printf("\nAverage Throughput[kbps] = %.2f",(recvdSize/(stopTime-startTime))*(8/1000))
	printf("\nStartTime=%.2f",startTime)
	printf("\nStopTime=%.2f\n",stopTime)
	
}
