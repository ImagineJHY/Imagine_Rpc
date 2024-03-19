cd proto

protoc --cpp_out=. Context.proto
protoc --cpp_out=. InternalMessage.proto

sed -i "s#Context.pb.h#Imagine_Rpc/Context.pb.h#g" Context.pb.cc
sed -i "s#InternalMessage.pb.h#Imagine_Rpc/InternalMessage.pb.h#g" InternalMessage.pb.cc

mv *.pb.h ../include/Imagine_Rpc/
mv *.pb.cc ../src/