# c_GPIO

c_GPIO is a rubygem for controlling GPIO Ports of raspberry PIs out of ruby.

It provides an easy to use interface for accessing the GPIO feature. c_GPIO is written in C to be as close as possible to the system.

I also wrote this as ruby c extension to learn a bit about C.

c_GPIO provides predefined classes for

  - LED
  - Buttons

There is a base class available as well which provides manual setting of direction (IN / OUT) and value (HIGH / LOW).

## Usage / Examples

Here you will find various examples for this gem.

#### Turning a LED on and off

    require 'c_gpio'
    
    led = GPIO::Led.new(2) # Initialize a LED connected to PIN 2
    
    led.turn_on! # Turn on the LED
    
    sleep(1) # Wait a second
    
    led.turn_off! # Turn off the LED
    
#### Connect a button to GPIO

    require 'c_gpio'
    
    button = GPIO::Button.new(2) # Initialize a button connected to PIN 2
    
    # pressed? will return true, if the button is being pressed,
    # otherwise it will return false
    if(button.pressed?) {
      puts "The button is currently pressed"
    }

#### Using the Base Class for reading custom parts

    require 'c_gpio'
    
    io = GPIO::Base.new(2) # We want to read from PIN 2
    
    io.direction = "in" # Setting the direction to "in", so we can read
    
    p io.value # will print "1" or "0" depending on what you connected
    
#### Using the Base Class for writing custom parts

    require 'c_gpio'
    
    io = GPIO::Base.new(2) # We want to write to PIN 2
    
    io.direction = "out" # Setting the direction to "out", so we can write
    
    io.value = "1" # will power the connected part on
    
    io.value = "0" # will power the connected part off



License
----

MIT


**Free Software, Hell Yeah!**
