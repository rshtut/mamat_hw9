#!/usr/bin/env bash

cat $1 > tmp_rule_file.txt
sed -i 's/ //g' tmp_rule_file.txt

cat tmp_rule_file.txt | while read line
do
	rule=$(awk -F# '{print $1}' <<< $line)
	if [ -z "$rule" ]; then
		continue
	fi
	for i in 1 2 3 4
	do
		cur_rule=$(awk -v var=$i -F, '{print $var}' <<< "$rule")
		while IFS = read -r inputline; do
			echo $inputline | ./firewall.exe $cur_rule >> packets.txt
		done
		sort packets.txt | uniq > sorted_packets.txt
		if [ $i -eq 0 ]; then
			cat sorted_packets.txt > collected_packets.txt
		else
			grep -f sorted_packets collected_packets.txt > uniq_packets.txt
			rm collected_packets.txt
			cat uniq_packets.txt > collected_packets.txt
			rm uniq_packets.txt
		fi
		rm sorted_packets.txt
	done
	cat collected_packets.txt > output_packets.txt
done

sort output_packets.txt | uniq
rm output_packets.txt

rm tmp_rule_file.txt