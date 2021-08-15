using Rhino.Geometry;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace PInvokeCSharpOpenNurbs
{
    public static class PInvoke
    {

        #region UnsafeMethods

        private const string dllName = "PInvokeON.dll";


        [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ReleaseInt(IntPtr arr, bool isArray=true); //release output indices array


        [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ReleaseFloat(IntPtr arr, bool isArray = true); // release input coordinates


        [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ReleaseDouble(IntPtr arr, bool isArray = true); // release input coordinates


        [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int Power2(int a);


        [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int UnsafeCollisionDetectionOBB(
            [MarshalAs(UnmanagedType.LPArray)] double[] PositionsXYZ,
            [MarshalAs(UnmanagedType.LPArray)] double[] XAxesXYZ, 
            [MarshalAs(UnmanagedType.LPArray)] double[] YAxesXYZ,
            [MarshalAs(UnmanagedType.LPArray)] double[] HalfSizeXYZ, 
            ulong numberOfBoxes,
            ref IntPtr pairs, ref int numberOfPairs
        );


        public static int[] CollisionDetectionOBB(Box[] OBB)
        {

            //////////////////////////////////////////////////////////////////////////////////////////
            /// INPUT Convert Box Parameters to PInvoke 
            //////////////////////////////////////////////////////////////////////////////////////////
            ulong numberOfBoxes = (ulong)OBB.Length;
            double[] PositionsXYZ = new double[numberOfBoxes * 3];
            double[] XAxesXYZ = new double[numberOfBoxes * 3];
            double[] YAxesXYZ = new double[numberOfBoxes * 3];
            double[] HalfSizeXYZ = new double[numberOfBoxes * 3];

            for(int i = 0; i < OBB.Length * 3; i+=3)
            {
                int id = i / 3;

                PositionsXYZ[i] = OBB[id].Center.X;
                PositionsXYZ[i + 1] = OBB[id].Center.Y;
                PositionsXYZ[i + 2] = OBB[id].Center.Z;

                XAxesXYZ[i] = OBB[id].Plane.XAxis.X;
                XAxesXYZ[i + 1] = OBB[id].Plane.XAxis.Y;
                XAxesXYZ[i + 2] = OBB[id].Plane.XAxis.Z;

                YAxesXYZ[i] = OBB[id].Plane.YAxis.X;
                YAxesXYZ[i + 1] = OBB[id].Plane.YAxis.Y;
                YAxesXYZ[i + 2] = OBB[id].Plane.YAxis.Z;

                HalfSizeXYZ[i] = OBB[id].X.Length * 0.5;
                HalfSizeXYZ[i + 1] = OBB[id].Y.Length * 0.5;
                HalfSizeXYZ[i + 2] = OBB[id].Z.Length * 0.5;
            }

            IntPtr pairsPointer = IntPtr.Zero;
            int numberOfPairs = 0;

            //////////////////////////////////////////////////////////////////////////////////////////
            /// METHOD Call the method
            //////////////////////////////////////////////////////////////////////////////////////////
            UnsafeCollisionDetectionOBB(PositionsXYZ, XAxesXYZ, YAxesXYZ, HalfSizeXYZ, numberOfBoxes, ref pairsPointer, ref numberOfPairs);

            ///////////////////////////////////////////////////////////////////////////
            // CONVERSION Convert Pointer to int array
            ///////////////////////////////////////////////////////////////////////////
            int[] pairsFlatArray = new int[numberOfPairs*2];
            Marshal.Copy(pairsPointer, pairsFlatArray, 0, pairsFlatArray.Length);

            //////////////////////////////////////////////////////////////////////////////////////////
            /// MEMORY Delete output from the memory
            //////////////////////////////////////////////////////////////////////////////////////////
            ReleaseInt(pairsPointer);

            //////////////////////////////////////////////////////////////////////////////////////////
            /// OUTPUT the result
            //////////////////////////////////////////////////////////////////////////////////////////
            return pairsFlatArray;
        }

        #endregion

    }
}
