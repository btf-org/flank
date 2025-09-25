class Flank < Formula
  desc "Test formula that installs the flank script"
  homepage "https://github.com/btf-org/flank"
  url "https://github.com/btf-org/flank/archive/refs/heads/main.tar.gz"
  version "0.1.0"
  sha256 "43119d8332e914fb665242ed2f44adab33508d2cb34c2ae0c8ce38a9a987ba34"



  def install
    bin.install "flank" => "flank" if File.exist?("flank")

    (prefix/"INSTALL_LOG.txt").write("Installed at #{Time.now}")
  end

  def post_install
    (var/"flank").mkpath
  end
end

