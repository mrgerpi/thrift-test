
extern "C" TSimpleServer* get_SERVICE_NAME_server(int port)
{
	shared_ptr<CLASS> handler(new CLASS());
	shared_ptr<TProcessor> processor(new PROCESSOR(handler));
	shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	shared_ptr<TTransportFactory> transportFactory(new (TFramedTransportFactory));
	shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TSimpleServer* server = new TSimpleServer(processor, serverTransport, transportFactory, protocolFactory);
	return server;
}

