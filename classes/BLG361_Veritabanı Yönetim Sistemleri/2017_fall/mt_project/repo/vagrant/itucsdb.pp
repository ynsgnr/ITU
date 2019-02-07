class itucsdb {

  package { "build-essential":
    ensure => present,
  }
  package { "git":
    ensure => present,
  }
  package { "libncurses-dev":
    ensure => present,
  }
  package { "libreadline-dev":
    ensure => present,
  }
  package { "libtar-dev":
    ensure => present,
  }
  package { "libz-dev":
    ensure => present,
  }
  package { "libbz2-dev":
    ensure => present,
  }
  package { "libjpeg-dev":
    ensure => present,
  }
  package { "libpng-dev":
    ensure => present,
  }
  package { "libfreetype6-dev":
    ensure => present,
  }
  package { "libxml2-dev":
    ensure => present,
  }
  package { "libxslt-dev":
    ensure => present,
  }
  package { "libssl-dev":
    ensure => present,
  }
  package { "libdb-dev":
    ensure => present,
  }
  package { "libsqlite3-dev":
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
  package { "postgresql":
    ensure => present,
  }
  package { "libpq-dev":
    ensure => present,
  }
  package { "phppgadmin":
    ensure => present,
  }

  # used for creating a PuTTy-compatible key file
  package { "putty-tools":
    ensure => present,
  }

}

include itucsdb
