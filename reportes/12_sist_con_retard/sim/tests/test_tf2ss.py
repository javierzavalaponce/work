import numpy as np

from tf2ss import tf2ss


def test_ejemplo_basico():
    A, B, C, D = tf2ss([1], [1, -3, 2])

    np.testing.assert_allclose(A, [[0, 1], [-2, 3]])
    np.testing.assert_allclose(B, [[0], [1]])
    np.testing.assert_allclose(C, [[1, 0]])
    np.testing.assert_allclose(D, [[0]])
