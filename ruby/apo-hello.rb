#!/usr/bin/ruby

# class Tukang Ucap 
class Mengucap
  def initialize(nama)
    @nama = nama.capitalize
  end
 
  def ucapkan
    puts "Hello #{@nama}!"
  end
end

# Create a new object
g = Mengucap.new("world")

# Output "Hello World!"
g.ucapkan

