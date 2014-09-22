Gem::Specification.new "c_gpio", "0.0.5" do |s|
  # [...]

  s.author      = ['hujiko']
  s.homepage    = "https://github.com/hujiko/c_GPIO"
  s.summary     = "Ruby gem to control GPIO ports of a raspberry PI"
  s.description = "Ruby gem to control GPIO ports of a raspberry PI"
  s.licenses    = ['MIT']

  s.extensions = %w[ext/c_gpio/extconf.rb]
end
