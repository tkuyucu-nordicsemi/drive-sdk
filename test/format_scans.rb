#!/usr/bin/env ruby

if $0 == __FILE__


p ARGV

File.open(ARGV[0], 'r').each do |line|
  next if line.include?(':')
  str_data = line.strip
  a = str_data.split(/ /)
  c_values = a.map { |e| "0x#{e}" }
  puts "{ #{c_values.join(", ")} };"
end

end
