Gem::Specification.new "c_gpio", "0.0.7" do |s|
  # [...]

  s.author       = ['hujiko']
  s.homepage     = "https://github.com/hujiko/c_GPIO"
  s.summary      = "Ruby gem to control GPIO ports of a raspberry PI"
  s.description  = "Ruby gem to control GPIO ports of a raspberry PI"
  s.licenses     = ['MIT']
  s.files        = Dir["CHANGELOG.md", "MIT-LICENSE", "README.md", "ext/**/*", "lib/**/*"]
  s.require_path = "lib"

  s.extensions = %w[ext/c_gpio/extconf.rb]
end
