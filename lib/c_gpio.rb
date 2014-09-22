module GPIO
  VERSION = '0.0.5'
end

require 'c_gpio/gpio'

class GPIO::Base
  def on_high(&block)
    Thread.new do
      wait_for_high(block)
    end
  end

  def on_low(&block)
    Thread.new do
      wait_for_low(block)
    end
  end
end

class GPIO::Button
  def on_press(&block)
    Thread.new do
      wait_for_low(block)
    end
  end

  def on_release(&block)
    Thread.new do
      wait_for_high(block)
    end
  end
end
