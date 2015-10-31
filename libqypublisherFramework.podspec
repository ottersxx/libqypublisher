Pod::Spec.new do |spec|
  spec.name         = 'libqypublisherFramework'
  spec.version      = '1.1.53'
  spec.license      = {
:type => 'Proprietary',
:text => <<-LICENSE
      Copyright 2015 QYVideo Ltd. All rights reserved.
      LICENSE
  }
  spec.homepage     = 'http://www.qyvideo.net/'
  spec.authors      = { 'Peng Bin' => 'pengbin@qyvideo.cn' }
  spec.summary      = 'libqypublisher help you publisher live video from ios mobile devices.'
  spec.description  = <<-DESC
    libqypublisher record live video from camera with software codec, and publish to rtmp server.
  DESC
  spec.platform     = :ios, '7.0'
  spec.requires_arc = true
  spec.ios.library = 'z', 'iconv', 'stdc++.6'
  spec.source = { :git => 'https://github.com/qyvideo/libqypublisher.git', :tag => '1.1.53'}
  spec.preserve_paths      = 'libqypublisher.framework'
  spec.public_header_files = 'libqypublisher.framework/Headers'
  spec.vendored_frameworks = 'libqypublisher.framework'
end
