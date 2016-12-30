import os
import os.path
from setuptools import setup, find_packages, Extension


prefix = os.getenv('PREFIX', '/usr/local')

ext_modules = [
    Extension('uhdvna._native',
              include_dirs=[os.path.join(prefix, 'include')],
              libraries=['uhd', 'boost_system'],
              library_dirs=[os.path.join(prefix, 'lib')],
              sources=['uhdvna/_native.cpp'])
]


setup(name='uhdvna',
      version='0.0.1.dev',
      description='USRP-based Vector Network Analyzer',
      long_description='',
      classifiers=[
          'Development Status :: 2 - Pre-Alpha',
      ],
      keywords='uhd usrp vna sdr vector network analyzer',
      ext_modules=ext_modules,
      url='https://github.com/storborg/uhdvna',
      author='Scott Torborg',
      author_email='storborg@gmail.com',
      license='GPL',
      packages=find_packages(),
      install_requires=[
      ],
      setup_requires=['pytest-runner'],
      tests_require=['pytest'],
      include_package_data=True,
      zip_safe=False,
      entry_points="""\
      [console_scripts]
      uhdvna = uhdvna.cmd:main
      """)
