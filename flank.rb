class Flank < Formula
  desc "Test formula that just sets up a data directory"
  version "0.1.0"
  url "file:///dev/null"


  def install
    (prefix/"INSTALL_LOG.txt").write("Installed at #{Time.now}")
  end

  def post_install
    (var/"flank").mkpath
  end
end

