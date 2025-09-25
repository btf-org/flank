class Flank < Formula
  desc "Test formula that installs the flank script"
  homepage "https://github.com/btf-org/flank"
  url "https://github.com/btf-org/flank/archive/refs/heads/main.tar.gz"
  version "0.1.0"
  sha256 "<REPLACE_WITH_TARBALL_SHA256>"



  def install
    bin.install "flank" => "flank" if File.exist?("flank")

    (prefix/"INSTALL_LOG.txt").write("Installed at #{Time.now}")
  end

  def post_install
    (var/"flank").mkpath
  end
end

