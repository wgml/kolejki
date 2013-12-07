#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T17:40:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kolejki
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    advanceddialog.cpp \
    qcustomplot.cpp \
    urand.cpp \
    System.cpp \
    show.cpp \
    saveToFile.cpp \
    Queue.cpp \
    nrand.cpp \
    Client.cpp \
    showplotswindow.cpp

HEADERS  += mainwindow.h \
    advanceddialog.h \
    qcustomplot.h \
    sleeper.h \
    urand.h \
    System.h \
    show.h \
    saveToFile.h \
    randSeed.h \
    Queue.h \
    nrand.h \
    Client.h \
    showplotswindow.h \
    boost/random.hpp \
    boost/random/xor_combine.hpp \
    boost/random/weibull_distribution.hpp \
    boost/random/variate_generator.hpp \
    boost/random/uniform_smallint.hpp \
    boost/random/uniform_real_distribution.hpp \
    boost/random/uniform_real.hpp \
    boost/random/uniform_on_sphere.hpp \
    boost/random/uniform_int_distribution.hpp \
    boost/random/uniform_int.hpp \
    boost/random/uniform_01.hpp \
    boost/random/triangle_distribution.hpp \
    boost/random/taus88.hpp \
    boost/random/subtract_with_carry.hpp \
    boost/random/student_t_distribution.hpp \
    boost/random/shuffle_output.hpp \
    boost/random/shuffle_order.hpp \
    boost/random/seed_seq.hpp \
    boost/random/ranlux.hpp \
    boost/random/random_number_generator.hpp \
    boost/random/random_device.hpp \
    boost/random/poisson_distribution.hpp \
    boost/random/piecewise_linear_distribution.hpp \
    boost/random/piecewise_constant_distribution.hpp \
    boost/random/normal_distribution.hpp \
    boost/random/negative_binomial_distribution.hpp \
    boost/random/mersenne_twister.hpp \
    boost/random/lognormal_distribution.hpp \
    boost/random/linear_feedback_shift.hpp \
    boost/random/linear_congruential.hpp \
    boost/random/lagged_fibonacci.hpp \
    boost/random/inversive_congruential.hpp \
    boost/random/independent_bits.hpp \
    boost/random/geometric_distribution.hpp \
    boost/random/generate_canonical.hpp \
    boost/random/gamma_distribution.hpp \
    boost/random/fisher_f_distribution.hpp \
    boost/random/extreme_value_distribution.hpp \
    boost/random/exponential_distribution.hpp \
    boost/random/discrete_distribution.hpp \
    boost/random/discard_block.hpp \
    boost/random/chi_squared_distribution.hpp \
    boost/random/cauchy_distribution.hpp \
    boost/random/binomial_distribution.hpp \
    boost/random/bernoulli_distribution.hpp \
    boost/random/additive_combine.hpp \
    boost/random/detail/vector_io.hpp \
    boost/random/detail/uniform_int_float.hpp \
    boost/random/detail/signed_unsigned_tools.hpp \
    boost/random/detail/seed_impl.hpp \
    boost/random/detail/ptr_helper.hpp

FORMS    += mainwindow.ui \
    advanceddialog.ui \
    showplotswindow.ui

OTHER_FILES += \
    makefile
