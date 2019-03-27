FROM pawelkorus/cpp-dev

USER root

RUN cd ~/ \
	&& git clone https://github.com/aws/aws-sdk-cpp.git

RUN cd ~/ \
	&& mkdir libs \
	&& cd libs \
	&& cmake -DBUILD_ONLY="s3" ~/aws-sdk-cpp \
	&& make \
	&& make install

RUN apt-get update \
	&& apt-get install -y --no-install-recommends \
		dolphin \
	&& rm -rf /var/lib/apt/lists/*

RUN apt-get update \
	&& apt-get install -y --no-install-recommends \
		dbus-x11 qt5ct breeze-icon-theme \
	&& rm -rf /var/lib/apt/lists/*

USER user

ENV QT_QPA_PLATFORMTHEME=qt5ct

RUN mkdir -p ~/.config/qt5ct \
	&& echo "[Appearance]" > ~/.config/qt5ct/qt5ct.conf \
	&& echo "icon_theme=breeze" >> ~/.config/qt5ct/qt5ct.conf

USER root

RUN apt-get update \
	&& apt-get install -y --no-install-recommends \
		qtbase5-dev extra-cmake-modules libkf5kio-dev \
	&& rm -rf /var/lib/apt/lists/*

RUN apt-get update \
	&& apt-get install -y --no-install-recommends \
		kde-cli-tools \
	&& rm -rf /var/lib/apt/lists/*

# Link .so file so that output location can be changed by user
RUN mkdir -p /usr/lib/x86_64-linux-gnu/qt5/plugins/kf5/kio && ln -s /home/user/out/kioaws.so /usr/lib/x86_64-linux-gnu/qt5/plugins/kf5/kio/kioaws.so

USER user
