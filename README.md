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

    # If you want to get notified, once a button is pressed or released,
    # You can easily use one (or both) of the following callbacks

    button.on_press do
        puts "You pressed da button"
    end

    button.on_release do
        puts "ou stopped pressing the button"
    end

#### Using the Base class for reading custom parts

    require 'c_gpio'

    io = GPIO::Base.new(2) # We want to read from PIN 2

    io.direction = :in # Setting the direction to "in", so we can read

    io.value # will return :high or :low depending on what your sensor says

#### Using the Base class for writing custom parts

    require 'c_gpio'

    io = GPIO::Base.new(2) # We want to write to PIN 2

    io.direction = :out # Setting the direction to "out", so we can write

    io.value = :high # will power the connected part on

    io.value = :low # will power the connected part off

#### Using callbacks of the Base class

Those callbacks can be used for both directions, "IN" and "OUT".
Using them you can observe, if your peripheral device changed the signal from HIGH to LOW or from LOW to HIGH.
If the direction is set to "OUT", you also can observe, if someone is changing the outgoing signal.

    require 'c_gpio'

    io = GPIO::Base.new(2) # We want to write to PIN 2

    io.direction = :in

    io.on_high do
        puts "signal changed to HIGH"
    end

    io.on_low do
        puts "signal changed to low"
    end



License
----

MIT


**Free Software, Hell Yeah!**

Finally
----

I wrote this as my fist c program and my first c extension.
I have to Idea if this code is looking pretty or optimized.

But I am open to everyone who wants to give feedback or collaborate in this.
