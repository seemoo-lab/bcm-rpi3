#!/usr/bin/env perl

use strict;
use warnings;

my $buffer;
my @bytes = ();
my $cnt = 0;
my $reverse = 0;
my $infile;
my $outfile;

my $num_args = $#ARGV + 1;
if ($num_args < 2) {
print "Usage: [-r] in_file out_file\n";
    exit;
}

if($ARGV[0] =~ '-r') {
    $reverse = 1;
    $infile = $ARGV[1];
    $outfile = $ARGV[2];
} else {
    $infile = $ARGV[0];
    $outfile = $ARGV[1];
}

print("Using infile: '$infile', outfile: '$outfile'\n");
# File size of $infile
my $ucode_len = -s $infile;

open(FH, '<:raw', $infile);
read(FH, $buffer, $ucode_len);
@bytes = unpack('C*',$buffer); # 'C*' multiple unsigned character
close(FH);

open(FHW, '>:raw', $outfile);
if(not $reverse) {
    # see FW function of bcm43438: wlc_bmac_wlc_ucode_write_byte(wlc_hw_info *wlc_hw, int ucode, unsigned int ucode_len) @ 0x44EC4
    while($cnt < $ucode_len) {
        $cnt += 7;
        my $byte1 = ($bytes[$cnt-3] << 16) | ($bytes[$cnt-4] << 24) | ($bytes[$cnt-1]) | ($bytes[$cnt-2] << 8);
        print FHW pack('I', $byte1); # 'I' 32 bit unsigned int
        my $byte2 = ($bytes[$cnt-6] << 8) | ($bytes[$cnt-7] << 16) | ($bytes[$cnt-5]);
        print FHW pack('I', $byte2);
    }
} else {
    while($cnt < $ucode_len) {
        $cnt += 8;
        my $byte1 = sprintf("%014x", ($bytes[$cnt-2] << 48) | ($bytes[$cnt-3] << 40) | ($bytes[$cnt-4] << 32) | ($bytes[$cnt-5] << 24) | ($bytes[$cnt-6] << 16) | ($bytes[$cnt-7] << 8) | ($bytes[$cnt-8]));
        print FHW pack('H*', $byte1); # 'H*' hex string (high nybble first)
    }
}
close(FHW);
