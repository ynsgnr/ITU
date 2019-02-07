class itucsdb2 {

  package { "libxft2":
    ensure => present,
  }
  package { "libxtst6":
    ensure => present,
  }
  package { "libxi6":
    ensure => present,
  }
  package { "libaio1":
    ensure => present,
  }
  package { "python3":
    ensure => present,
  }
  package { "python3-dev":
    ensure => present,
  }
  package { "python3-setuptools":
    ensure => present,
  }
  package { "python3-pip":
    ensure => present,
  }

  # used for creating a PuTTy-compatible key file
  package { "putty-tools":
    ensure => present,
  }

}

include itucsdb2
